import cv2
import glob
import numpy as np
import os
import math

def face_detection(gray, frame, face_cascade):
    faces = face_cascade.detectMultiScale(gray, 1.01, 5)

    fddb_photos = r'C:\Users\Администратор\Desktop\FDDB\FDDB-folds\FDDB-fold-01.txt'
    fddb_annotations = r'FDDB-fold-01-ellipseList.txt'
    with open(fddb_annotations, 'r') as annotations:
        print('text')
        for file in annotations:
            file_split = file.rsplit('/')
            #file_clean = r'C:\Users\Администратор\Desktop\FDDB\FDDB-folds\FDDB-fold-01-ellipseList.txt' + file.rstrip('\n')
            with open(r'C:\Users\Администратор\Desktop\FDDB\FDDB-folds\FDDB-fold-01-ellipseList.txt', 'w+') as annotation:
                for canvas in range(int(next(annotations))):
                    this_line = next(annotations)
                    this_line_split = this_line.split()
                    major_axis_radius = float(this_line_split[0])
                    minor_axis_radius = float(this_line_split[1])
                    angle = float(this_line_split[2])
                    center_x = float(this_line_split[3])
                    center_y = float(this_line_split[4])
                    E_w, E_h = img.size
                    E_x = math.sqrt(major_axis_radius ** 2 * math.cos(angle) ** 2 \
                                       + minor_axis_radius ** 2 * math.sin(angle) ** 2)
                    E_y = math.sqrt(major_axis_radius ** 2 * math.sin(angle) ** 2 \
                                       + minor_axis_radius ** 2 * math.cos(angle) ** 2)
                    x = center_x / E_w
                    y = center_y / E_h
                    w = (2 * E_x) / E_w
                    h = (2 * E_y) / E_h
                    detection_score = 1
                    print(x,y,w,h)

    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 255, 0), 3)
    return frame

if __name__ == '__main__':
    path = glob.glob(r"C:\Users\Администратор\Desktop\FDDB\originalPics\*.img")
    i = 0
    for img in path:
        n = cv2.imread(img)
        print(img)

        face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
        gray = cv2.cvtColor(n, cv2.COLOR_BGR2GRAY)
        canvas = face_detection(gray, n, face_cascade)

        cv2.imshow('image', n)
        cv2.imwrite('saveme_%i.jpg' % i, n)
        if cv2.waitKey(0) & 0xFF == ord('s'):
            break
        i += 1






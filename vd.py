#haarcascade_frontalface_default.xml

import cv2, time, camera
import numpy as np

if __name__ == '__main__':
    camera = camera.def_web(1280, 720)
    cascade = cv2.CascadeClassifier(haar)

    while True:
        ret, frame = camera.read()

        if not ret:
            break

        grayFrame = frame[:, :, :]
        cv2.cvtColor(grayFrame, cv2, COLOR_BGR2GRAY)

        faces = cascade.detectMultiScale(grayFrame)

        for (x,y,w,h) in faces:
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 3)

        cv2.imshow('Frame name', frame)

        if cv2.waitKey(1) & 0xFF == ord('n'):
            break

    camera.release()
    cv2.destroyAllWindows()


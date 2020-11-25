import cv2
import glob

def face_detection(gray, frame, face_cascade):
    faces = face_cascade.detectMultiScale(gray, 1.01, 5)
    print(faces)
    for (faceX, faceY, faceWidth, faceHeight) in faces:
        cv2.rectangle(frame, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (255, 255, 0), 3)
    return frame

if __name__ == '__main__':
    path = glob.glob(r"images\*.jpg")
    cv_img = []
    i=0
    for img in path:
        n = cv2.imread(img)
        print(img)
    #    cv_img.append(n)

        face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
        gray = cv2.cvtColor(n, cv2.COLOR_BGR2GRAY)
        canvas = face_detection(gray, n, face_cascade)

        while True:
            cv2.imshow('image', n)
            if cv2.waitKey(0) & 0xFF == ord('s'):
                break
        cv2.imwrite('saveit_%i.jpg' %i, n)
        i =i + 1

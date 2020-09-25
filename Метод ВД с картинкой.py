import cv2

def face_detection(gray, frame):
    faces = face_cascade.detectMultiScale(gray, 1.01, 5)
    for (faceX, faceY, faceWidth, faceHeight) in faces:
        cv2.rectangle(frame, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (255, 255, 0), 3)
        return frame

if __name__ == '__main__':
    img = cv2.imread('image.jpg', 0)
    face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")


    cv2.imshow('image', img)
    k = cv2.waitKey(0) & 0xFF == ord('s')
    cv2.imwrite('messigray.png',img)
    cv2.destroyAllWindows()
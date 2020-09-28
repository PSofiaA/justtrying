import cv2

def face_detection(gray, frame, face_cascade):
    faces = face_cascade.detectMultiScale(gray, 1.01, 5)
    print(faces)
    for (faceX, faceY, faceWidth, faceHeight) in faces:
        cv2.rectangle(frame, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (255, 255, 0), 3)
    return frame

if __name__ == '__main__':
    img = cv2.imread('image.jpg')
    face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    canvas = face_detection(gray, img, face_cascade)

    while True:
        cv2.imshow('image', canvas)
        if cv2.waitKey(0) & 0xFF == ord('s'):
            break
    cv2.imwrite('saveit.png',img)
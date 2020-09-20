import cv2
if __name__ == '__main__':
    cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
    webcam = cv2.VideoCapture(0)

    while True:
        ret, frame = webcam.read()
        if not ret:
            break

        grayFrame = frame[:, :, :]  #копию делаем и преображаем в серый цыет
        cv2.cvtColor(grayFrame, cv2.COLOR_BGR2GRAY)  #перевод из цветного в серый

        faces = cascade.detectMultiScale(grayFrame) #

        for (faceX, faceY, faceWidth, faceHeight) in faces:
            cv2.rectangle(frame, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (255, 0, 0), 3)

        cv2.imshow('something', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    webcam.release()
    cv2.destroyAllWindows()

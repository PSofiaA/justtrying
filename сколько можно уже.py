import cv2

# показываю каскад хаара
video_capture = cv2.VideoCapture(0)
face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

while True:
    ret, frame = video_capture.read()
    if not ret:
        break

def face_detection(gray, frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.01, 5)
    for (faceX, faceY, faceWidth, faceHeight) in faces:
        cv2.rectangle(frame, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (255, 0, 0), 3)
        return frame

# захват рамкой

    canvas = face_detection(gray, frame)
    cv2.imshow('Face Detection', canvas)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# завершение работв программы
video_capture.release()
cv2.destroyAllWindows()

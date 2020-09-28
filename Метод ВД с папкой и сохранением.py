import cv2
import glob

def face_detection(gray, frame, face_cascade):
    faces = face_cascade.detectMultiScale(gray, 1.01, 5)
    print(faces)
    for (faceX, faceY, faceWidth, faceHeight) in faces:
        cv2.rectangle(frame, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (255, 255, 0), 3)
    return frame

if __name__ == '__main__':
    path = glob.glob(r"C:\Users\Администратор\PycharmProjects\Метод Виолы-Джонса\images")
    cv_img = []
    for img in path:
        n = cv2.imread(img)
        cv_img.append(n)

    # face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")

    # gray = cv2.cvtColor(cv_img, cv2.COLOR_BGR2GRAY)
    #canvas = face_detection(gray, cv_img, face_cascade)

    #while True:
        #cv2.imshow('image', canvas)
        #if cv2.waitKey(0) & 0xFF == ord('s'):
            #break
    #cv2.imwrite('saveit.png', cv_img)

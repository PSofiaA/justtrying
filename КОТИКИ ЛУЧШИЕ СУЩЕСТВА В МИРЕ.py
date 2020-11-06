import cv2
import os
import math
import numpy as np
import itertools
import time

file_paths = (r'.\FDDB\FDDB-folds\FDDB-fold-02.txt')
file_annotations = (r'.\FDDB\FDDB-folds\FDDB-fold-02-ellipseList.txt')
op_path = (r".\FDDB\originalPics")
def bb_intersection_over_union(boxA, boxB):
    xA = max(boxA[0], boxB[0])
    yA = max(boxA[1], boxB[1])
    xB = min(boxA[2], boxB[2])
    yB = min(boxA[3], boxB[3])
    interArea = max(0, xB - xA + 1) * max(0, yB - yA + 1)
    boxAArea = (boxA[2] - boxA[0] + 1) * (boxA[3] - boxA[1] + 1)
    boxBArea = (boxB[2] - boxB[0] + 1) * (boxB[3] - boxB[1] + 1)
    iou = interArea / float(boxAArea + boxBArea - interArea)
    return iou
if __name__ == '__main__':
    with open(file_annotations, 'r') as f1:
        rec_lines = f1.readlines()
        rec_lines_num = len(rec_lines)
        rec_lines_id = 0
        i = 0
        #print('time = ', timeit.default_timer())
        TP_total = []
        FP_total = []
        FN_total = []
        while rec_lines_id < rec_lines_num:
            rec_line = rec_lines[rec_lines_id].strip()
            image_name = rec_line
            pat = (os.path.join(op_path, image_name + ".jpg"))
            image_name = os.path.normpath(pat)
            if not os.path.isfile(image_name):
                continue
            else:
                    pass
            start = time.time()
            img = cv2.imread(image_name)
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
            faces = face_cascade.detectMultiScale(gray, 1.01, 15)
            p0 = []
            for (faceX, faceY, faceWidth, faceHeight) in faces:
                cv2.rectangle(img, (faceX, faceY), (faceX + faceWidth, faceY + faceHeight), (2, 0, 152), 2)
                p0.append([faceX, faceY, faceX + faceWidth, faceY + faceHeight])
            stop = time.time()
            print('elapsed time=', stop - start)
            print("p", p0)
            k = int(rec_lines[rec_lines_id + 1].strip())
            g0 = []
            for face_id in range(k):
                rec_line = rec_lines[rec_lines_id + 2 + face_id].strip()
                rec_line_split = rec_line.split(' ')
                major_axis_radius = float(rec_line_split[0])
                minor_axis_radius = float(rec_line_split[1])
                angle = float(rec_line_split[2])
                center_x = float(rec_line_split[3])
                center_y = float(rec_line_split[4])
                whyineedthis = int(rec_line_split[6])
                # перевожу эллипс в прямоугольник
                one = (math.pi * angle) / 180.0
                sin = math.sin(one) ** 2
                cos = math.cos(one) ** 2
                a = major_axis_radius ** 2
                b = minor_axis_radius ** 2
                RW = int(math.sqrt(2 / ((sin / a) + (cos / b))))
                RH = int(math.sqrt(2 / ((sin / b) + (cos / a))))
                RX = int(center_x - (RW / 2))
                RY = int(center_y - (RH / 2))
                cv2.rectangle(img, (RX, RY), (RX + RW, RY + RH), (255, 255, 0), 3)
                g0.append([RX, RY, RX + RW, RY + RH])
                #print(type(g0))
            #print(type(p0))

            dim1_det =(np.array(p0).shape[0])
            print("dim1", dim1_det)
            dim2_det = (np.array(p0).shape[1])
            print("dim2", dim2_det)
            dim1_gt = (np.array(g0).shape[0])
            dim2_gt = (np.array(g0).shape[1])

            groundtruth_total = np.zeros((1, dim1_gt, dim2_gt))
            print(groundtruth_total)
            groundtruth_total[0] = g0
            print('gtrt', groundtruth_total)
            detections_total = np.zeros((1, dim1_det, dim2_det))
            detections_total[0] = p0

            detections_iou_total = []
            groundTruth_iou_total = []
            detections_d = detections_total[0]
            groundtruth_d = groundtruth_total[0]
            detection_groundtruth_iou = np.zeros((detections_d.shape[0], groundtruth_d.shape[0]))

            for gt in range(len(groundtruth_d)):
                #print(len(groundtruth_d))

                for dt in range(len(detections_d)):
                    #print(len(detections_d))
                    det_box = detections_d[dt]
                    #print(gt)
                    print('det_box', det_box)
                    gt_box = groundtruth_d[gt]
                    print('gt_box', gt_box)
                    iou = bb_intersection_over_union(det_box, gt_box)
                    print('iou', iou)
                    detection_groundtruth_iou[dt][gt] = iou
                print('detection_groundtruth_iou: ')
                print(detection_groundtruth_iou)
                detections_iou = list(np.max(detection_groundtruth_iou, 1))
                groundTruth_iou = list(np.max(detection_groundtruth_iou, 0))
                print('detections_iou:', detections_iou)
                print('groundtruth_iou:', groundTruth_iou)
                #detections_iou_total = detections_iou_total + detections_iou
                #groundTruth_iou_total = groundTruth_iou_total + groundTruth_iou
            #print('detections_iou_total: ', detections_iou_total)
            #print('groundTruth_iou_total: ', groundTruth_iou_total)

            TP = [i for i in detections_iou if i >= 0.5]
            TP_num = len(TP)
            TP_total.append(TP_num)
            FP = [i for i in detections_iou if i < 0.5]
            FP_num = len(FP)
            FP_total.append(FP_num)
            FN = [i for i in groundTruth_iou if i < 0.5]
            FN_num = len(FN)
            FN_total.append(FN_num)

            Recall = TP_num / float(TP_num + FN_num)
            Recall_total = sum(TP_total)/float(sum(TP_total)+sum(FN_total))
            Precision = TP_num / float(TP_num + FP_num)
            Precision_total = sum(TP_total)/float(sum(TP_total)+sum(FP_total))
            AFT = 0 if Precision_total + Recall_total <= 0 else 2 * Precision_total * Recall_total/(Precision_total+Recall_total)
            FT = (2*sum(TP_total))/(2*sum(TP_total)+sum(FP_total)+sum(FN_total))
            if Precision+Recall <= 0:
                F = 0
            else:
                F = 2 * Precision * Recall / (Precision + Recall) #tp fn fp для суммы

            print('TP_num:', TP_num)
            print('FP_num:', FP_num)
            print('FN_num:', FN_num)
            print('Recall:', Recall)
            print('Precision:', Precision)
            #print('Fscore:', F) #tp fn fp для суммы

            print('TP_total', TP_total)
            print('FP_total', FP_total)
            print('FN_total', FN_total)
            #print('Recall_total:', Recall_total)
            #print('Precision_total', Precision_total)
            print('Ftotal', FT)
            print('AFT', AFT)

            newpath = (r'.\NEWFDDB')
            cv2.imwrite(os.path.join(newpath, 'saveit_%i.jpg' % i), img)

            rec_lines_id = rec_lines_id + 1 + 1 + k * 1
            i = i + 1
            if i>5:
                break

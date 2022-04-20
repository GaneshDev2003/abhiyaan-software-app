import cv2 as cv
import numpy as np
import random as rng
#captures the video frame by frame
cap = cv.VideoCapture('bolt_test_pothole.mp4')
while (cap.isOpened()):
    ret, im1 = cap.read()
    im1 = cv.resize(im1, (540, 380), fx = 0, fy = 0,
                         interpolation = cv.INTER_CUBIC)
    #the image is blurred to reduce computation and to get better contours
    im = cv.blur(im1,(5,5))
    #frame is converted rgb to grayscale
    imgray = cv.cvtColor(im, cv.COLOR_BGR2GRAY)
    
    #we get the contours for the frame
    ret, thresh = cv.threshold(imgray, 127, 255, 0)
    contours, hierarchy = cv.findContours(thresh, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)

    RectBoundary = [None]*len(contours)
    EllipseBoundary = [None]*len(contours)
    for i, c in enumerate(contours):
            #for each contour of height more than 5 we fit an ellipse and a bounding rectangle
            if c.shape[0] > 5:
                RectBoundary[i] = cv.minAreaRect(c)
                EllipseBoundary[i] = cv.fitEllipse(c)
        
    for i, c in enumerate(contours):
            color = (0, 0, 0)
            e = EllipseBoundary[i]
            #we check if the contour was actually and ellipse by comparing with area of the fitted ellipse
            if c.shape[0] > 5 and cv.contourArea(c) < 1000 and cv.contourArea(c) > 200 and abs(cv.contourArea(c) - 0.785375*e[1][0]*e[1][1]) < 10:
                cv.ellipse(im1, EllipseBoundary[i], color, 2)
                box = cv.boxPoints(RectBoundary[i])
                box = np.intp(box)
                cv.drawContours(im1, [box], 0, color)

    cv.imshow('Contours', im1)
    if cv.waitKey(25) & 0xFF == ord('q'):
        break
cap.release()
cv.destroyAllWindows()

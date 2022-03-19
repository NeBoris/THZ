import cv2
import numpy as np
import matplotlib.pyplot as plt
from IPython.display import Image

def viewImage(image, name_of_window):
    cv2.imwrite('/home/boris/work/THZ/BiCa0.4FeO3/Area/BiCa0.4FeO3_v1_before.jpg', image)
    cv2.namedWindow(name_of_window, cv2.WINDOW_NORMAL)
    cv2.imshow(name_of_window, image)
    cv2.waitKey(0)
    cv2.destroyWindow()

image = cv2.imread("/home/boris/work/THZ/BiCa0.4FeO3/4_12_21_Impedance.jpg", 0)


# for i in range(343, 1134):
#     for j in range(1390, 1610):
#         if image[i][j - 1] > 70 and image[i][j] > 70 and image[i][j + 1] < 60:
#             for k in range(0, 72):
#                 image[i][j + k] = 80

# for i in range(0, 1384):
#     for j in range(497, 1100):
#         if i < 1.0429*j + 513 and image[i][j - 1] == image[i][j] == image[i][j + 1] == 80:
#             image[i + 1][j] = 80



# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#         if image[i][j] >= 80:
#             image[i][j] = 255

#for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#       if image[i][j] < 80:
#            image[i][j] = 0

# for i in range(1, int(image.shape[0]) - 1):
#     for j in range(1, int(image.shape[1]) - 1):
#         if image[i + 1][j] < 10 and image[i][j + 1] < 10 and image[i - 1][j] < 10 and image[i][j - 1] < 10:
#             image[i][j] = 0

# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#        if (j - 1130)**2 + (i - 950)**2 < 460**2:
#           image[i][j] = 255

#for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#       if (j - 1228)**2 + (i - 946)**2 < 180**2:
#          image[i][j] = 255
# # # 

#for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#       if (j - 1210)**2 + (i - 1000)**2 > 550**2:
#           image[i][j] = 0

#for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#       if (j - 1230)**2 + (i - 1250)**2 > 700**2:
#           image[i][j] = 0

for i in range(0, int(image.shape[0])):
    for j in range(0, int(image.shape[1])):
       if (j - 1200)**2 + (i - 690)**2 > 560**2:
           image[i][j] = 0

for i in range(0, int(image.shape[0])):
    for j in range(0, int(image.shape[1])):
        if image[i][j] < 70:
           image[i][j] = 0

for i in range(0, int(image.shape[0])):
    for j in range(0, int(image.shape[1])):
        if image[i][j] >= 70:
           image[i][j] = 255
           
counter = 0

for i in range(0, int(image.shape[0])):
   for j in range(0, int(image.shape[1])):
       if  image[i][j] > 90:
        counter = counter + 1





# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#        if image[i][j] <= 95 :
#           image[i][j] = 0

# for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#        if j < (0.00068*(i - 970)**2 + 83) and image[i][j] < 35:
#           image[i][j] = 255


# for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#        if j < (0.00068*(i - 948)**2 + 83) and j < 140 and image[i][j] >= image[i][j + 1] >= image[i][j + 2] >= image[i][j + 3] and image[i][j + 4] >= 250:
#           for k in range(0, j + 3):
#             image[i][k] = 255

# for i in range(0, int(image.shape[0])):
#    for j in range(0, int(image.shape[1])):
#        if j >= (0.003*(i - 184)**2 + 17) and j < 500 and image[i][j] >= 250 and image[i][j + 1] <= 100 and image[i][j - 1] <= 100 and image[i + 1][j] <= 100 and image[i - 1][j] <= 100:
#           image[i][j] = 40

# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#         if j >= (0.003*(i - 184)**2 + 17) and j < 500 and image[i][j] >= 250 and image[i][j + 1] <= 100 and image[i][j - 1] <= 100 and image[i + 1][j] <= 100:
#           image[i][j] = 40

# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#         if j >= (0.003*(i - 184)**2 + 17) and j < 500 and image[i][j] >= 250 and image[i][j + 1] <= 100 and image[i][j - 1] <= 100 and image[i - 1][j] <= 100:
#           image[i][j] = 40

# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#         if j >= (0.003*(i - 184)**2 + 17) and j < 500 and image[i][j] >= 250 and image[i][j + 1] <= 100 and image[i + 1][j] <= 100 and image[i - 1][j] <= 100:
#           image[i][j] = 40

# for i in range(0, int(image.shape[0])):
#     for j in range(0, int(image.shape[1])):
#         if j >= (0.003*(i - 184)**2 + 17) and j < 500 and image[i][j] >= 250 and image[i][j - 1] <= 100 and image[i + 1][j] <= 100 and image[i - 1][j] <= 100:
#           image[i][j] = 40

cv2.putText(image, "BiCa0.4FO3: " + str(counter) + " = " + str(counter / 4040100) + " cm^2", (100, 100), cv2.FONT_HERSHEY_SIMPLEX, 1, (255), 3)

print(counter)

viewImage(image, "Image")


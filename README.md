# Opencv-Circle-Detection-Without-Houghcircle
I tried an algorithm with some math calculations to detect circles.

# [Youtube Link](https://www.youtube.com/watch?v=lTbOKh_wJF0)

 # Algorithm Steps:
 
  1- Convert image to grayscale
  
  2- Apply median filter to eliminate noise
  3- Apply canny to get binary image
  4- Find contours with the efficient parameters
  5- Apply minAreaRect function to get the fitted rectangles for each contour
  6- Filter contours by their length not to get small contours(noisy contours)
  7- Get the center of fitted recttangles
  8- Compare each contour's point with the center of fitted rectangles
  9- Make a comparison and get the results
 
 # Requirements
 
  This algorithm works well in these conditions:
 
  1- The pictures should be taken parallel to surface(camera should be parallel to target circles)
  2- Shadows shouldn't exist or they should be eliminated
  3- Occlusion

# visualize_Trajectory_KITTI

Visualize the ground truth poses as a 2-D trajectory.

The data come from the [KITTI odometry groud truth poses](http://www.cvlibs.net/datasets/kitti/eval_odometry.php).

## Data format:

N x 12:

|         | R_11 | R_12 | R_13 | t_1 | R_21 | R_22 | R_23 | t_2 | R_31 | R_32 | R_33 | t_3 |
| ------- | ---- | ---- | ---- | --- | ---- | ---- | ---- | --- | ---- | ---- | ---- | --- |
| Frame_0 | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... |
| Frame_1 | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... |
| ...     | ...  | ...  | ... | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... |
| Frame_i | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... |
| ...     | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... |
| Frame_N | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... | ...  | ...  | ...  | ... |

the row of which corresponds to a 3x4 transformation matrix:

T = 

    [R_11, R_12, R_13, t_1;]
    
    [R_21, R_22, R_23, t_2;]

    [R_31, R_32, R_33, t_3;]


Note, the i'th coordinate system is: 

* x pointing the right of the car.

* y pointing downwards to the ground.

* z pointing forwards of the car.


Each such transformation matrix take a point in the i'th coordinate
system and project it into the first (=0th) coordinate system. 

Hence, the translational part (3x1 vector of column 4) corresponds to the pose of the
left camera coordinate system in the i'th frame with respect to the first (=0th) frame.
This is the **TRAJECTORY** that we want here.

So, Row i represents the i'th pose of the left camera coordinate system with respect to the first (=0th) frame.


## Trajectory

Here, the trajectory is shown in the planar of x and z, with x pointing to the right, and z pointing forwards.

<a href="https://github.com/LijunSun90/visualize_Trajectory_KITTI/blob/master/doc/trajectory_ground_truth_KITTI.mp4" target="_blank"><img src="https://github.com/LijunSun90/visualize_Trajectory_KITTI/blob/master/doc/trajectory_ground_truth_KITTI.png" 
alt="The video of the trajectory" height="180" border="3" /></a>

## Calling convention:

./visualize_Trajectory_KITTI [dir_name of the dataset]

./visualize_Trajectory_KITTI ../dataset/

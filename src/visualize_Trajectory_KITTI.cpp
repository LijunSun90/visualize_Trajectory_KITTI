// visualize_Trajectory_KITTI.cpp
// Calling convention:
// ./visualize_Trajectory_KITTI [dir_name of the dataset]
// ./visualize_Trajectory_KITTI ../dataset/

#include <istream>
#include <ostream>
#include <opencv2/opencv.hpp>

using namespace std;

void help(char* argv[]){
    cout << "\nCalling convention: \n" 
    << "\n    ./visualize_Trajectory_KITTI [dir_name of the dataset]\n" 
    << "\n For example, \n"
    << "\n    ./visualize_Trajectory_KITTI ../dataset/\n\n"
    << endl;
}


void parsePosesFile(
    string poses_file,
    vector< cv::Mat > & Rs,
    vector< cv::Mat > & ts){

    // Load the file.
    ifstream loaded_poses(poses_file.c_str());
    if(!loaded_poses.is_open()){
        cout << "\nERROR: cannot open the file " + poses_file << endl;
        exit(-1);
    }
    //
    string lines, entry;
    istringstream linestream;
    //
    while(getline(loaded_poses, lines)){
        linestream.clear();
        linestream.str(lines);

        cv::Mat R = cv::Mat::zeros(3, 3, CV_64F);
        cv::Mat t = cv::Mat::zeros(3, 1, CV_64F);

        // R and t.
        //
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 4; col++){
                linestream >> entry;
                // cout << entry << endl;
                if(col == 3){
                    t.at<double>(row) = atof(entry.c_str());
                } else {
                    R.at<double>(row, col) = atof(entry.c_str());
                }
            }
        } 
        Rs.push_back(R);
        ts.push_back(t);
        cout << "\nR: \n" << R 
        << "\nt: \n" << t << endl;


    } // while(getline(loaded_poses, lines)).
    

} // END OF parsePosesFile().


/**
 * @param Rs, the collection of the total rotation matrix to the reference.
 * @param ts, the collection of the total translation matrix to the reference.
 */
void visualize_trajectory(vector< cv::Mat > Rs, vector< cv::Mat > ts){
   
    // trajectory: Horizontal: x; Vertical: z.
    cv::Mat trajectory = cv::Mat::zeros(600, 600, CV_8UC3);    
    cv::Point pose_current;
    //
    cv::Mat R, t;
    for(size_t ix = 0; ix < Rs.size(); ix++){
        R = Rs[ix];
        t = ts[ix];

        pose_current = cv::Point(t.at<double>(0) + 300, t.at<double>(2) + 100);
        cv::circle(trajectory, pose_current, 1, cv::Scalar(255, 0, 0), 1, CV_FILLED);
        cv::imshow("trajectory", trajectory);
        cv::moveWindow("trajectory", 0, 0);
        if(cv::waitKey(5) == 27) exit(0);
    } // END OF for(size_t ix = 0; ix < Rs.size(); ix++).

} // END OF visualize_trajectory().


int main(int argc, char* argv[]){

    // Read the input parameters.
    if(argc < 2){
        cout << "ERROR: Wrong number of parameters!" << endl;
        help(argv);
    }

    string dir_name = argv[1];

    // Parse the poses file.
    //
    string poses_file = dir_name + "/poses/00.txt";
    vector< cv::Mat > Rs, ts;
    parsePosesFile(poses_file, Rs, ts);

    // Visualize the trajectory.
    //
    visualize_trajectory(Rs, ts);

    cv::destroyAllWindows();
    return 0;
}


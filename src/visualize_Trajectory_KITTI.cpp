// visualize_Trajectory_KITTI.cpp
// Calling convention:
// ./visualize_Trajectory_KITTI [dir_name of the dataset]
// ./visualize_Trajectory_KITTI ../dataset/

#include <istream>
#include <ostream>
#include <opencv2/opencv.hpp>

using namespace std;

void help(char* argv[]){
}

void visualize_trajectory(string poses_file){
   // Ground truth poses.
    //
    vector< cv::Mat > Rs_truth, ts_truth;
    // Load the file.
    ifstream loaded_poses(poses_file.c_str());
    if(!loaded_poses.is_open()){
        cout << "ERROR: cannot open the file " + poses_file << endl;
        exit(-1);
    }
    //
    string lines, entry;
    istringstream linestream;
    // trajectory: Horizontal: x; Vertical: z.
    cv::Mat trajectory = cv::Mat::zeros(600, 600, CV_8UC3);    
    cv::Point pose_current;
    //
    while(getline(loaded_poses, lines)){
        linestream.clear();
        linestream.str(lines);

        cv::Mat R_truth = cv::Mat::zeros(3, 3, CV_64F);
        cv::Mat t_truth = cv::Mat::zeros(3, 1, CV_64F);

        // R_truth.
        //
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                linestream >> entry;
                // cout << entry << endl;
                R_truth.at<double>(row, col) = atof(entry.c_str());
            }
        } 
        Rs_truth.push_back(R_truth);
        // t_truth.
        //
        for(int row = 0; row < 3; row++){
            linestream >> entry;
            t_truth.at<double>(row) = atof(entry.c_str());
        }
        ts_truth.push_back(t_truth);
        cout << t_truth << endl;
        
        pose_current = cv::Point(t_truth.at<double>(0) * 1000 + 300, t_truth.at<double>(2));
        cv::circle(trajectory, pose_current, 1, cv::Scalar(255, 0, 0), 1, CV_FILLED);
        cv::imshow("trajectory", trajectory);
        if(cv::waitKey(10) == 27) exit(0);


    } // while(getline(loaded_poses, lines)).
}


int main(int argc, char* argv[]){

    // Read the input parameters.
    if(argc < 2){
        cout << "ERROR: Wrong number of parameters!" << endl;
        help(argv);
    }

    string dir_name = argv[1];

    string poses_file = dir_name + "/poses/00.txt";
    visualize_trajectory(poses_file);

    cv::destroyAllWindows();
    return 0;
}


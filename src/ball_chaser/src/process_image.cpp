#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget srv;

    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    if (!client.call(srv))
    {
        ROS_INFO("Failed to call DriveToTarget");
    }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    static int frameCnt = 0;
    int white_pixel = 255;
    int left, middle;
    left = img.step/3;
    middle = 2*left;
    // should be control message to control also these values. now fixed
    float speed = 0.2;
    float left_direction = 0.3;
    float straight = 0.0;
    float right_direction = -0.3;

    for (int i = 0; i < img.height; i++)
    {
        for (int j = 0; j < img.step; j+=3)
        {
            int pixel_r = (uint)img.data[i * img.step + j];
            int pixel_g = (uint)img.data[i * img.step + j + 1];
            int pixel_b = (uint)img.data[i * img.step + j + 2];
            
            if (pixel_r == white_pixel && pixel_b == white_pixel && pixel_r == white_pixel)
            {
                //ROS_INFO("white pixel - height: %d, width: %d", i, j);
                if (j < left) 
                {
                    drive_robot(speed, left_direction);
                }
                else if (j < middle) 
                {
                    drive_robot(speed, straight);
                }
                else // ball is in right sector
                {    
                    drive_robot(speed, right_direction);
                }
                
                frameCnt = 0;
                return;
            }
        }
    }
    frameCnt++;
    //ROS_INFO("No white pixels, %d, %d", frameCnt++, img.step);
    // do nothing, actually should map the world and search the ball
    drive_robot(0, 0);
    return;

}

int main(int argc, char **argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
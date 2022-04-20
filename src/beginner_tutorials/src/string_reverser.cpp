#include "ros/ros.h"
#include "std_msgs/String.h"

#include "sstream"
#include<string.h>
using namespace std;
//reverses string word by word
string reverse_string(string s)
{
     string ans;
    string temp;
    int prev_space=-1;
    for(int i=0;i<s.size();i++)
    {
        if(isspace(s[i]))
        {
            temp = s.substr(prev_space+1,i-prev_space-1);
              cout<<temp<<endl;
            reverse(temp.begin(),temp.end());
           
            ans.append(temp);
            ans.append(1,' ');
            prev_space = i;
        }
    }
    temp = s.substr(prev_space+1,s.size()-prev_space-1);
   
    reverse(temp.begin(),temp.end());
    ans.append(temp);
    return ans;
}
class SubPub 
{
  public:
    SubPub(){}
    SubPub(std::string sub_topic, std::string pub_topic, int queueSize)
    {
      pub  = nh.advertise<std_msgs::String>(pub_topic,queueSize);
      sub = nh.subscribe<std_msgs::String>(sub_topic,queueSize, &SubPub::callBack,this);
    }
    void callBack(const std_msgs::String::ConstPtr& msg)
    {
      string s = reverse_string(msg->data.c_str());
      ROS_INFO("Recieved msg is : %s" , msg->data.c_str());
      std_msgs::String ms;
      std::stringstream ss;
      ss<<s;
      ms.data = ss.str();
      pub.publish(ms);
      ROS_INFO("Published msg is : %s" , ms.data.c_str());
    }
  protected:
    ros::NodeHandle nh;
    ros::Subscriber sub;
    ros::Publisher pub;
};

 int main(int argc, char **argv)
 {
     ros::init(argc,argv,"reverser");
     SubPub reverser_node("/team_abhiyaan","/maet_naayihba",1000);
     ros::spin();
     return 0;
 }
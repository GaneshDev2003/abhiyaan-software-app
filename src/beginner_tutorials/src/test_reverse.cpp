 #include<bits/stdc++.h>
 #include<string.h>
 using namespace std;
 int main()
 {
     string s = "hello world";
     
      string ans;
    string temp;
    int prev_space=-1;
    for(int i=0;i<s.size()-1;i++)
    {
        if(s[i]==' ')
        {
            temp = s.substr(prev_space+1,i-prev_space-i-1);
            reverse(temp.begin(),temp.end());
            ans.append(temp);
            ans.append(1,' ');
            prev_space = i;
        }
    }
    temp = s.substr(prev_space+1,s.size()-prev_space-1);
    reverse(temp.begin(),temp.end());
    ans.append(temp);

    cout<<ans;

 }
#include<bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(NULL));
    int num_frames= 10, N=5;
    vector<int> buff; //receiver side buffer
    
    int n=5, j=0, p=0, flag=0, ack, out=0;
    vector<int> data; // window that is going to be sent at a time.
    while(1)
    {
       //populate data vector with the frames to be sent.
        for(j=p; j<p+n && j<num_frames; j++)
            {
                data.push_back(j);
                if(data.size()==n)
                {
                    p = j+1;
                    break;
                }
        }
        // this case is for window that has frames_count < window_size.
        // push -1.
        while(data.size()<n)
        {
            data.push_back(-1);
        }    
        for(int i=0; i<n; i++)
        {
            //start a new window
            if(flag)
            {
                cout << "\nNew Window: ";
                for(int k=0; k<n; k++)
                    cout << data[k] << " ";
                cout << "\n";
                flag=0;
            }
            // frame tp be sent is empty
            if(data[i]==-1)
            {
                out = 1;
                break;
            }
            cout << "Sender: Frame sent: " << data[i] << "\n";
            ack = rand()%2;
            // negative acknowledgment so push frmae into receiver buffer.
            if(ack == 0)
            {
                buff.push_back(data[i]);
            }
            else // send positive acknowledgment
            {
                cout << "Receiver: Frame " << data[i] << " received.\n";
            }
        }
        //clear data
        data.clear();
        //transfer contents from buffer to data vector.
        for(int k=0; k<buff.size(); k++)
            data.push_back(buff[k]);
        // clear buffer
        buff.clear();
        // set flag for next transmission
        flag=1;
        //Break from loop if data vector has only empty slots or all frames are sent.
        if(out==1 || (p>=num_frames&&buff.size()==0))
            break;
    }
    
    return 0;
}
        
        

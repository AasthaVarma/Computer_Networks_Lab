#include<bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(NULL));
    int N = 5;
    //int ws = N, wr = 1;
    int ack = 1;
    bool will_get_ack; // signals whether acknowlwdgment received or not.
    int next_case=0; // number of frames to be sent again.
    int num_frames = 10, flag=1;
    int j = N-1, i, p=-1; 
    for(i=0; i<num_frames; i++)
    {
        // start a new window.
        if(flag)
        {
            cout <<"\nNew window!\n";
            flag=0;
        }
        cout << "Sender:Frame sent is: " << i <<  "\n";
        // 
        if(next_case==0)
        {
            will_get_ack = rand()%2;
            // positive acknowledgement
            if(will_get_ack==1)
            {
                cout << "Receiver:Frame received, Ack sent.\n";
                //j++;    
            }
            else 
            {
                cout << "Receiver: Frame not received, Ack not sent "<< next_case << "\n";
                //this is for last case when frame_to_be_sent_count < window_size
                if(i+N-1>=num_frames)
                {
                    p = i;
                    break;
                }  
                // this i will be the first frame of window which will be sent again. 
                next_case++;
                //i = j-N;
            }
        }
        else
        {
            // this discarded frame need to be sent again in the next frame.
            next_case = next_case+1;
            cout << "Receiver:Frame discarded - " << i << "\n";
            //p = i;
            
        }
        // end of window
        if(next_case == N)
        {
            flag=1;
            cout << "i: " << i << "\n";
            
            i=i-N;
            
            next_case = 0;
                
        }
    }
    
    // last case:
    for(int j=p; j<num_frames; j++)
        {
            cout << "Sender:Frame sent is: " << j << "\n";
            cout << "Receiver:Frame received, Ack sent.\n";
        }
    
    return 0;
}

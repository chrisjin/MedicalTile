#include"DiffImage.h"
float  DiffImage::ForVoxTimeSequence(vector<int>& arr)
{
	vector<float> st;
	for(int i=0;i<arr.size();i++)
	{
		st.push_back(arr[i]);
	}
	vector<float> smooth;
	for(int i=0;i<arr.size();i++)
	{
		float add=0;
		for(int j=-1;j<=1;j++)
		{
			if(i+j>=0&&i+j<arr.size())
				add+=st[i+j];
			else if(i+j<0)
			{
				add+=st[0];
			}
			else
			{
				add+=st[st.size()-1];
			}
		}
		smooth.push_back(add/3.0);
	}
	vector<float> diff;
	diff.push_back(0);
	for(int i=1;i<smooth.size();i++)
	{
		diff.push_back(smooth[i]-smooth[i-1]);
	}
	
	int pos;
	int sum=-INT_MAX;
	for(int i=0;i<diff.size();i++)
	{
		if(diff[i]>=sum)
		{
			sum=diff[i];
			pos=i;
		}

	}
	//for(int i=pos;i<diff.size();i++)
	//{
	//	if(diff[i]<0)
	//	{
	//		pos=i;
	//	}
	//}
	return pos;
}
#include <iostream>
#include <cstring>
using namespace std;

char gen[]="10001000000100001";
int genarr=strlen(gen),i,j,k;
int check=0;
char d[30], md[30], cs[20], rem[20];
int n,m;

void crc_16()
{
    for(j=0;j<genarr;j++)
    cs[j]=md[j];
    cout<<endl;
    
  for(i=0;i<n;i++)
  {
    if(cs[0]=='1')
    {
    	for (int i=0;i<genarr;i++)
        	rem[i]=((cs[i]==gen[i])?'0':'1');
	}
    else
    {
      for(k=0;k<genarr;k++)
      rem[k]=cs[k];
    }

    for(k=0;k<genarr-1;k++)
      cs[k]=rem[k+1];
      
      cs[k]=md[genarr+i];
  }
}


int main()
{
cout<<"Enter data: " <<endl;
cin>>d;
  n=strlen(d);

  for (i=0;i<n;i++) md[i]=d[i];
  
  cout<<endl;

  for (i=n;i<n+genarr-1;i++)
  md[i]='0';

  m=strlen(md);
 
  crc_16();
 
  for (i=n,j=1;i<n+genarr-1;i++,j++) md[i]=rem[j];
  m=strlen(md);
  cout<<"\n============================ SENDER MODULE =========================================\n";
  cout<<endl<<"Codeword generated : ";
  for ( i=0;i<m;i++) cout<<md[i];
  cout<<"\n====================================================================================\n"<<endl;
  
  cout<<"\n============================ RECEIVER MODULE ======================================="<<endl;
  cout<<"Received Codeword : "; cin>>md;
  m=strlen(md);
  cout<<"\n\n";
  crc_16();
  
  for (i=1;i<genarr;i++)
  {
    if(rem[i]=='1'){
      check=1;
      break;
    }
  }
  
  if(check)    cout<<"\n\nERROR IN RECEIVED CODEWORD!"<<endl;
  else      cout<<"\n\nNO ERROR!"<<endl;
  cout<<"======================================================================================="<<endl;

}


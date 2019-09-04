#include<stdio.h>
#include<string.h>
#include<math.h>

int*  sender(char *str) {
	int i,j,k,n,m,ch,ch_,cz,val;
	static int dw[1000]={0};
	int cw[1000]={0};
	
	n = strlen(str);
	for(i=0;i<n;i++)    dw[i] = (int)str[i] - 48;
	
	for(i=1;i<n;i++)    if(pow(2,i) >= n+i+1) break;
	m=i;
	cz = m+n;
	
	for(i=0;i<m;i++)  cw[(int)pow(2,i)-1] = 2;

	for(i=0,j=(n-1);i<cz;i++)
	if(cw[i]!=2) { cw[i] = dw[j]; j--; }
    
    ch_ = (int)pow(2,m);
    
	for(i=0;i<m;i++) {
    	ch = (int)pow(2,i) ;
		val = 2;
		for(j=ch;j<=cz;j+=ch) {
			for(k=0;k<ch && j<=cz;k++,j++){
			if (cw[j-1]!=2 && val == 2) 
			val = cw[j-1]; 
			else val ^= cw[j-1];
	    }
		}
		cw[ch-1] = val;
	}
	
	for(i=cz-1,j=0;i>=0;i--,j++)  dw[j] = cw[i];
	dw[j] = cz;
	return dw;
}

int receiver(int *cw) {
	int i,j,k,cz,n,m,val,ch,ch_;
	int dw[1000]={0},r[15]={0};
	val = cw[0];
	printf("\n=========================================\n");
	printf("Received codeword : ");
	for(i=0;cw[i]<2;i++) printf("%d ",cw[i]);
	printf("\n=========================================\n");
	for(i=0;cw[i]<2;i++) if(i!=0) val ^= cw[i]; 
	cz = i;
	if(val == 0) return -1;
	else {
    	for(i=cz-1,j=0;i>=0;i--,j++)  dw[i] = cw[j];
    	
    	for(i=1;i<cz;i++)    if(pow(2,i) > cz) break;
	    m=i;
    	n = cz - m;
    	ch_ = (int)pow(2,m);
    
	    for(i=0;i<m;i++) {
    	ch = (int)pow(2,i) ;
		val = 2;
		for(j=ch;j<=cz;j+=ch) {
			for(k=0;k<ch && j<=cz;k++,j++)
			if (dw[j-1]!=2 && val == 2) val = dw[j-1];
			else val ^= dw[j-1];
		}
		r[m-i-1] = val;
	    }
		val=0;
		for(i=0;i<m;i++) val += (pow(2,i)*r[m-i-1]);
	    return val;
	}
}
int main() {
	int i,j,n,*cw,cz;
	char dataword[1000];
	printf("Dataword : ");
	scanf("%s",dataword);
	cw = sender(dataword);
	printf("Codeword generated : ");
	for(i=0;cw[i]<2;i++) printf("%d ",cw[i]);
	cz = cw[i];
	printf("\n----------------------------------------------------------------------\n");
	printf("DO you wish to add error \nEnter valid error position (1 - size of codeword) <yes>\n Enter 0<no> ? \n");
	scanf("%d",&i);
	if (i>=1 && i<=cz) cw[cz-i] = !cw[cz-i];
	n = receiver(cw);
	if(n==-1) printf("\nNO ERROR");
	else printf("\nERROR AT position %d in codeword",n);
}

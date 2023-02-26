inline void getfail(char *s){
	//求fail函数
	int n = strlen(s+1);
	for(int i=0; i<=n; i++)
		fail[i] = 0;
	for(int i = 2, j = 0; i <= n; i++){
		while(j && s[j+1] != s[i])
			j = fail[j];
		if(s[j+1] == s[i])
			++j;
		fail[i] = j;
	}
}
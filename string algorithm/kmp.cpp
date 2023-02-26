inline auto getfail(string s){
	//求fail函数
	int n = s.length();
	vector<int>fail(n, -1);
	for(int i = 1, j = -1; i < n; i++){
		while(~j && s[j+1] != s[i])
			j = fail[j];
		if(s[j+1] == s[i])
			++j;
		fail[i] = j;
	}
	return fail;
}
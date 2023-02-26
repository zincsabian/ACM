//51nod最大全1子矩阵
//悬线法， 实际上就是单调栈优化dp
int ans = 0;
for(int i=1; i<=n; i++){
    int top = 0;
    for(int j=1; j<=m; j++){
        a[i][j] = read();
        if(!a[i][j])
            U[i][j] = 0;
        else 
            U[i][j] = U[i-1][j] + 1;
        while(top&&U[i][j]<=U[i][s[top]])
            top--;
        L[i][j] = s[top] + 1;
        s[++top] = j;
    }
    s[++top] = m+1;
    for(int j=m; j; j--){
        while(top&&U[i][j]<=U[i][s[top]])
            top--;
        R[i][j] = s[top] - 1;
        s[++top] = j;
    }
    for(int j=1; j<=m; j++)
        ans = max(ans, U[i][j]*(R[i][j]-L[i][j]+1));
}
printf("%d\n", ans);
 n=1000;
fd=load('C:\Users\jonah\Desktop\ph141\assignment3\out0.c');
point=fd(:,2);
x=fd(:,3);
y=fd(:,4);
z=fd(:,5);
vx=fd(:,6);
vy=fd(:,7);
vz=fd(:,8);

tf=[];xf=[];yf=[];
i=ones(n);
for j=1:length(x)
    for k=1:n
        
    if point(j)==k-1
        xf(i(k),k)=x(j);
        yf(i(k),k)=y(j);
        zf(i(k),k)=z(j);
        vxf(i(k),k)=vx(j);
        vyf(i(k),k)=vy(j);
        vzf(i(k),k)=vz(j);
        i(k)=i(k)+1;
    end
    end
end
animate_demo3
picture=imread('1.jpg');
x=size(picture,1);
y=size(picture,2);
texture=uint8(zeros(x,y));
table=uint8(zeros(2,256));
%temp3=uint8(1);
num=uint8(0);
for index=0:1:255
    %变为相应的二进制数
    temp1=uint8(zeros(1,8));
    index1=1;
    temp2=index;
    while temp2
          temp1(1,index1)=mod(temp2,2);
          temp2=floor(temp2/2);
          index1=index1+1;
    end
    %计算跳数count
    count=0;
    for index1=1:1:7
        if temp1(1,index1)~=temp1(1,index1+1) 
            count=count+1;
        end
    end
    if temp1(1,1)~=temp1(1,8)
        count=count+1;
    end

    if count<=2
       table(1,index+1)=index;
       if(index<59)
          num=num+1;
       end
    else table(1,index+1)=59;
    end
     
end
temp=1;
for index=1:1:256
    if(table(1,index)~=59)
      if(temp==num+1)
       temp=temp+1;       
      end
       table(2,index)=temp;
      temp=temp+1;
    else table(2,index)=num+1;
    end
end
%初始化table完毕
%计算均匀的LBP算子
for i=2:1:x-1
    for j=2:1:y-1
        neighbor=uint8(zeros(1,8));
        neighbor(1,1)=picture(i-1,j-1);
        neighbor(1,2)=picture(i-1,j);
        neighbor(1,3)=picture(i-1,j+1);
        neighbor(1,4)=picture(i,j+1);
        neighbor(1,5)=picture(i+1,j+1);
        neighbor(1,6)=picture(i+1,j);
        neighbor(1,7)=picture(i+1,j-1);
        neighbor(1,8)=picture(i,j-1);
        center=picture(i,j);
        temp=uint8(0);
        for k=1:1:8
             temp =temp+ (neighbor(1,k) >= center)* 2^(k-1);
        end
        texture(i,j)=table(1,temp+1);
        
       
    end
end
imshow(texture);
disp(texture);
fid = fopen('out.txt','wt');
fprintf(fid,'%d',texture);
fclose(fid);
  
  img=imread('2b.jpg');
  imgGray=rgb2gray( img );
  img1=histeq( imgGray );   
  F=imresize(img, 0.5,'nearest');
  J=imresize(img, [64,64],'nearest');
  K=imrotate(img, 30);
  figure,
  subplot(2,4,1) , imshow( img );
  title( 'ԭͼ' )
  subplot(2,4,2) , imshow( imgGray );
  title( '�Ҷ�ͼ' )
  subplot(2,4,3) , imshow( img1 );
  title( '���⻯��' )
  subplot(2,4,4) , imhist( imgGray , 64 );
  title( 'ԭͼ' )
  subplot(2,4,5) , imhist( img1 , 64 );
  title( '���⻯��' )
  subplot(2,4,6) , imshow(J);
  title( '�淶Ϊ64*64' )
  subplot(2,4,7) , imshow( F );
  title( '0.5������' )
  subplot(2,4,8) , imshow( K );
  title( '��ת30��' )

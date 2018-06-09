 #version 330 core  

 in vec4 vertColor;
 in vec2 TexCoord;
 
 out vec4 FragColor;

 uniform sampler2D texture1;
 
 void main()  
 {  
 	FragColor = texture(texture1, TexCoord);  
 };
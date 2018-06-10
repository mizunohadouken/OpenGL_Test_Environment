 #version 330 core  

 in vec4 vertColor;
 in vec2 TexCoord;
 
 out vec4 FragColor;

 uniform sampler2D texture1;
 uniform sampler2D texture2;
 uniform float mixer;
 
 void main()  
 {  
 	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixer);  
 };
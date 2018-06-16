 #version 330 core  

 layout (location = 0) in vec4 aPos; 
// layout (location = 1) in vec4 aColor;
 layout (location = 2) in vec2 aTexCoord;
 
 out vec4 vertColor;
 out vec2 TexCoord;
 
 uniform mat4 mvpMat;

 void main()  
 {  
 	gl_Position = mvpMat * aPos;
	
	TexCoord = aTexCoord;	
 };
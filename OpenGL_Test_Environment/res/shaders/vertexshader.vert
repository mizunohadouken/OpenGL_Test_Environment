 #version 330 core  

 layout (location = 0) in vec4 aPos; 
 layout (location = 1) in vec4 aColor;
 layout (location = 2) in vec2 aTexCoord;
 
 out vec4 vertColor;
 out vec2 TexCoord;

 void main()  
 {  
 	gl_Position = aPos;
	
	vertColor = aColor;
	TexCoord = aTexCoord;	
 };
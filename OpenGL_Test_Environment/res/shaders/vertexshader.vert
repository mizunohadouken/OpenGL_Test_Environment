 #version 330 core  

 layout (location = 0) in vec4 aPos; 
 layout (location = 1) in vec4 color;
 uniform float offset;

 out vec4 vertColor;

 void main()  
 {  
	vertColor = aPos;
 	gl_Position = aPos;
 };
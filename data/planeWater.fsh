uniform vec4 u_color1;
uniform vec4 u_color2;

in float v_depth; // Receive depth value from vertex shader

out vec4 PixelColor;


void main()
{
    PixelColor = mix(u_color2, u_color1, (v_depth));
}
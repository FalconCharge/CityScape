uniform vec4 u_color1;
uniform vec4 u_color2;
uniform vec4 u_color3;
uniform vec4 u_color4;

in float v_depth; // Receive depth value from vertex shader

out vec4 PixelColor;


void main()
{
    vec4 seafoamGreen = vec4(0.498, 1.0, 0.831, 1.0); // Seafoam Green (#7FFFD4)
    vec4 turquoise = vec4(0.251, 0.878, 0.816, 1.0); // Turquoise (#40E0D0)
    vec4 oceanBlue = vec4(0.0, 0.412, 0.580, 1.0); // Ocean Blue (#006994)
    vec4 deepSeaBlue = vec4(0.0, 0.0, 0.545, 1.0); // Deep Sea Blue (#00008B)

    float depthFactor = clamp(v_depth, 0.0, 1.0);

    PixelColor = mix(deepSeaBlue, oceanBlue, (depthFactor));
}
























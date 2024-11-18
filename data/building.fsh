uniform vec3 u_color;

out vec4 PixelColor;  // User-defined output variable

void main() {
    PixelColor = vec4(u_color, 1.0);  // Assign color to the output
}

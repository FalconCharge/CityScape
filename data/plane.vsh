uniform mat4 mvp;

uniform float uScale;
uniform float vScale;

in vec4 a_position;
in vec2 a_uv1;
out vec2 v_uv1;

void main()
{
    gl_Position = mvp * a_position;
	v_uv1 = a_uv1 * vec2(uScale, vScale) * 6;  
}



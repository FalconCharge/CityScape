uniform mat4 mvp;
uniform mat4 worldIT;
uniform float uScale;
uniform float vScale;

in vec4 a_position;
in vec2 a_uv1;
in vec3 a_normal;

out vec2 v_uv1;
out vec3 v_normal;


void main()
{
    gl_Position = mvp * a_position;
    
	v_uv1 = a_uv1 * vec2(uScale, vScale) * 2;  

    v_normal = (worldIT * vec4(a_normal, 0.0)).xyz;
}



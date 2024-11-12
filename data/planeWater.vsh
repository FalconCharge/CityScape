uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
uniform float time;

in vec3 a_position;
out float v_depth;

void main() {

    vec3 pos = a_position;
    pos.y += abs(sin(time + pos.x) /2);
    pos.y += abs(sin((time + pos.z) * 2));

    v_depth = pos.y;

    gl_Position = projection * view * world * vec4(pos, 1.0);
}


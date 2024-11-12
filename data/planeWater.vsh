uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
uniform float time;
uniform bool wave1;
uniform bool wave2;

in vec3 a_position;
out float v_depth;

void main() {

    vec3 pos = a_position;
    /*
    if(wave1 && wave2){
        pos.y += abs(sin(time + pos.x * 1.5)) * 1.25;
        pos.y += abs(sin(time + pos.z/3));
    }
    else if(wave2){
        pos.y += abs(sin(time + pos.z/3));
    }
    else{
        pos.y += abs(sin(time + pos.x * 1.5)) * 1.25;
    }*/
    pos.y += abs(sin(time + pos.x * 1.5)) * 1.25;

    v_depth = pos.y;

    gl_Position = projection * view * world * vec4(pos, 1.0);
}


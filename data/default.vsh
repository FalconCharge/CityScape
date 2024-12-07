uniform mat4 mvp;

in vec4 a_position;

void main()
{
    gl_Position = mvp * a_position;
}


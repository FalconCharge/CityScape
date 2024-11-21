in vec2 v_uv1;

in vec3 debugColor;

uniform sampler2D tex;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(tex, v_uv1);

    //PixelColor = vec4(v_uv1, 0.0, 1.0);
}
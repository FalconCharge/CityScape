
in vec2 v_uv1;        
in vec3 v_normal;

uniform sampler2D tex;  // Texture sampler
uniform vec3 u_lightDir;  // Direction of the light source (normalized)
uniform vec3 u_lightColor; // Color of the light
uniform vec3 u_ambientLight; // Ambient light color

out vec4 PixelColor;  // Final color output

void main()
{
    // Sample the texture color
    vec4 texColor = texture(tex, v_uv1);

    // Normalize the normal to ensure it's unit length
    vec3 normal = normalize(v_normal);

    // Calculate the diffuse lighting using the Lambertian reflection model
    float diff = max(dot(normal, -u_lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor; // Diffuse lighting color

    //add ambient light
    vec3 ambient = u_ambientLight; 

    // Combine the diffuse and ambient light with the texture color
    vec3 finalColor = texColor.rgb * (ambient + diffuse);

    // Output the final color
    PixelColor = vec4(finalColor, texColor.a);
}

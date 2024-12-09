in vec2 v_uv1;        // Interpolated UV coordinates from the vertex shader
in vec3 v_normal;     // Interpolated normal vector from the vertex shader

uniform sampler2D tex;  // Texture sampler
uniform vec3 u_lightDir;  // Direction of the light source (normalized)
uniform vec3 u_lightColor; // Color of the light
uniform vec3 u_ambientLight; // Ambient light color (optional)

out vec4 PixelColor;  // Final color output

void main()
{
    // Sample the texture color using the UV coordinates
    vec4 texColor = texture(tex, v_uv1);

    // Normalize the normal to ensure it's unit length
    vec3 normal = normalize(v_normal);

    // Calculate the diffuse lighting using the Lambertian reflection model
    float diff = max(dot(normal, -u_lightDir), 0.0); // The dot product gives us the cosine of the angle between the normal and light direction
    vec3 diffuse = diff * u_lightColor; // Diffuse lighting color

    // Optionally, add ambient light (ambient light doesn't depend on the normal)
    vec3 ambient = u_ambientLight; 

    // Combine the diffuse and ambient light with the texture color
    vec3 finalColor = texColor.rgb * (ambient + diffuse);

    // Output the final color (with alpha channel from the texture)
    PixelColor = vec4(finalColor, texColor.a);
}

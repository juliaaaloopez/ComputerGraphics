// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec2 v_uv; //texture coordinates
varying vec3 v_world_position;

// pass our texture in uniform type (Image)
uniform sampler2D u_texture;

void main()
{
	// Set the ouput color per pixel
    vec4 texture_color = texture2D(u_texture, v_uv);

    gl_FragColor = texture_color;
}

varying vec2 v_uv;
//we can use time but we can use also an integer
uniform float u_time;
uniform sampler2D u_texture;
uniform float u_subtask;

void main()
{
    vec4 texture_color= texture2D(u_texture, v_uv);
    gl_FragColor= texture_color;

    if (u_subtask==1.0){
        vec2 center = vec2(0.5);
        vec2 relative_coords = v_uv - center;
        vec2 rotated_coords = vec2(relative_coords.x * cos(u_time) - relative_coords.y * sin(u_time), relative_coords.x * sin(u_time) + relative_coords.y * cos(u_time));
        vec2 rotated_uvs = rotated_coords + center;
        clamp(rotated_uvs, 0.0, 1.0);
        vec4 rotated_color = texture2D(u_texture, rotated_uvs);
        gl_FragColor = rotated_color;
    }

    if (u_subtask==2.0){
        const float pixelation_interval = 5.0;
        float time_factor = mod(u_time, pixelation_interval) / pixelation_interval;
        float pixelation_level = mix(5.0, 30.0, time_factor);
        vec2 pixel_size = vec2(1.0) / vec2(pixelation_level);
        vec2 coords = floor(v_uv / pixel_size);
        vec2 text_coords = coords * pixel_size;
        vec4 pixelation_color = texture2D(u_texture, text_coords);
        gl_FragColor = pixelation_color;

    }
   
}


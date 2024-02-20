varying vec2 v_uv;
//we can use time but we can use also an integer
uniform float u_time;
uniform sampler2D u_texture;

void main()
{
    //fragment shader
    //argv alpha value vector 4
    //A
    //gl_FragColor = vec4(v_uv.x, 0.0, 1.0-v_uv.x, 0.0); //everything RED if first component is 1.0
    //if we put v_uv.x we will have a horizontal gradient
    //with sinus we change the instensity of one of the colors
    //we overlap the two colors by adding 1.0-v_uv.x
    
    /*
     //B
    vec2 center = vec2(0.5); //we will define our center (of rectangle)
    float dist_ = distance(center, v_uv);
    vec3 final_color = vec3(dist_);
    gl_FragColor = vec4(final_color, 0.0);*/
    
    /*
    //C
    float blur = 0.15;
    float red = smoothstep(0.4 - blur, 0.4, fract(v_uv.x * 5.0)) - smoothstep(0.6, 0.6 + blur, fract(v_uv.x * 5.0));
    float blue = smoothstep(0.4 - blur, 0.4, fract(v_uv.y * 5.0)) - smoothstep(0.6, 0.6 + blur, fract(v_uv.y * 5.0));
    gl_FragColor = vec4(red, 0.0, blue, 1.0);*/
    
    //D
    
    /*vec2 uv = v_uv * 16.0;
    float red = smoothstep(0.5, 0.75, uv.x) * smoothstep(0.5, 0.75, uv.y);
    float green = 1.0 - smoothstep(0.5, 0.75, uv.x) * smoothstep(0.5, 0.75, uv.y);
    float blue = 0.0;
    float alpha = 0.0;
    vec3 color = vec3(red, green, blue);
    float diagonal = 1.0 + (uv.x + uv.y);
    gl_FragColor = vec4(diagonal * 0.045, 1.0 - (diagonal * 0.045), 0.0, 1.0);*/
    
    //E
    /*vec2 uv = v_uv * 16.0; //number of squares in row/column
    bool black = mod(floor(uv.x) + floor(uv.y), 2.0) < 1.0; //check if even or odd
    gl_FragColor = black ? vec4(0.0, 0.0, 0.0, 1.0) : vec4(1.0, 1.0, 1.0, 1.0);*/
    //do this with step
    
    //F
    
    
    //3.2
    //vec4 texture_color = texture2D(u_texture, v_uv);
    //gl_FragColor = texture_color;
    
    //A2
    /*float grayscale = (texture_color[0]+texture_color[1]+texture_color[2])/3.0;
    gl_FragColor = vec4(grayscale, grayscale, grayscale, texture_color[3]);*/
    
    
    //B2
    /*vec3 inverted_color = vec3(1.0-texture_color[0], 1.0-texture_color[1], 1.0-texture_color[2]);
    gl_FragColor = vec4(inverted_color, texture_color[3]);*/
    
    //C2
    /*float grayscale = (texture_color[0]+texture_color[1]+texture_color[2])/3.0;
    vec3 yellow = vec3(1.0, 1.0, 0.0) * grayscale;
    gl_FragColor = vec4(yellow, texture_color[3]);*/
    
    //D2
    /*float grayscale = (texture_color[0]+texture_color[1]+texture_color[2])/3.0;
    float threshold = 0.5;
    
    vec3 black_white = step(threshold, grayscale) * vec3(1.0); //step is either 0 or 1
    //if step == 0, then vec3(0.0, 0.0, 0.0) so pure black
    //if step == 1, then vec3(1.0, 1.0, 1.0) so pure white
    gl_FragColor = vec4(black_white, texture_color[3]);*/
    
    
    //E2
    /*vec2 center = vec2(0.5); //we will define our center (of rectangle)
    float dist_text = distance(v_uv, center);
    float vignette = smoothstep(0.05, 0.7, dist_text);
    gl_FragColor = mix(texture_color, vec4(0.0, 0.0, 0.0, 1.0), vignette); //mix between texture color, black and the size of the vignette as a factor*/
    
    //F2
    /*float noise_x = noise1(v_uv.x + u_time*0.1);
    float noise_y = noise1(v_uv.y + u_time*0.1);
    
    vec2 distorted = v_uv + vec2(noise_x, noise_y)*0.1;
    vec4 distorted_col = texture2D(u_texture, distorted);
    gl_FragColor = distorted_col;*/
    
    //3.3 ROTATION
    vec2 center = vec2(0.5);
    vec2 relative_coords = v_uv - center;
    vec2 rotated_coords = vec2(relative_coords.x * cos(u_time) - relative_coords.y * sin(u_time), relative_coords.x * sin(u_time) + relative_coords.y * cos(u_time));
    vec2 rotated_uvs = rotated_coords + center;
    clamp(rotated_uvs, 0.0, 1.0); 
    vec4 rotated_color = texture2D(u_texture, rotated_uvs);
    gl_FragColor = rotated_color;
    
}

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
    
    //B
    /*vec2 center = vec2(0.5); //we will define our center (of rectangle)
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
    // Map UV coordinates to screen space
    /*vec2 screenUV = v_uv * 2.0 - 1.0;

    // Get a noise value based on screen position
    float noiseValue = noise1(vec3(screenUV * 5.0, 0.0));

    // Quantize the noise value to create a pixelated effect
    float pixelSize = 0.1; // Adjust this value to control pixel size
    float quantizedNoise = floor(noiseValue / pixelSize + 0.5) * pixelSize;

    // Color degradation effect from blue to red
    vec3 degradationColor = vec3(v_uv.x, 0.0, 1.0 - v_uv.x);

    // Combine degradation effect with pixelation
    vec3 color = mix(vec3(0.0, 1.0, 0.0), degradationColor, quantizedNoise);

    // Render the color
    gl_FragColor = vec4(color, 1.0);*/
    
    
    //E
    /*vec2 uv = v_uv * 16.0; // number of squares. In this case we want 16 x 16 squares.
    float black = step(0.5, mod(floor(uv.x) + floor(uv.y), 2.0)); //we use the step function to calculate whether the square is black or white.
    gl_FragColor = vec4(vec3(1.0 - black), 1.0);*/
    
    //F
    // Define the center of the screen in UV coordinates
     vec2 center = vec2(0.5, 0.5);

     // Define the wave parameters
     float frequency = 10.0; // Adjust as needed
     float amplitude = 0.1; // Adjust as needed

     // Calculate the wave profile using a sine function
     float wave = sin((v_uv.x - center.x) * frequency) * amplitude + center.y;

     // Create the wave silhouette
     float silhouette = smoothstep(wave - 0.02, wave + 0.02, v_uv.y);

     // Calculate the gradient factor based on the distance from the top and bottom of the screen
     float gradientFactor = smoothstep(0.0, 0.5, min(abs(v_uv.y - center.y), abs(1.0 - v_uv.y - center.y)));

     // Interpolate between black and green based on the gradient factor
     vec4 gradientColor = mix(vec4(0.0, 1.0, 0.0, 1.0), vec4(0.0, 0.0, 0.0, 1.0), gradientFactor);

     // Interpolate between the gradient color and dark green based on the silhouette
     vec4 finalColor = mix(gradientColor, vec4(0.0, 1.0-v_uv.y, 0.0, 1.0), silhouette); //rgb

     // Output the final color with full opacity
     gl_FragColor = finalColor;
    
    
    
    
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
    /*float blurRadius = 0.005; // Change this value based on your preference

    vec3 blurredColor = vec3(0.0);
    float samples = 8.0;

    for(float i = -samples/2.0; i <= samples/2.0; i++){
        for(float j = -samples/2.0; j <= samples/2.0; j++){
            float offset = blurRadius * i;
            vec2 offsetCoord = v_uv + vec2(offset, blurRadius * j);
            blurredColor += vec3(texture2D(u_texture, offsetCoord));
        }
    }

    blurredColor /= float(samples * samples);
    gl_FragColor = vec4(blurredColor, texture_color[3]);*/

    
    
    //3.3 ROTATION
    /*vec2 center = vec2(0.5);
    vec2 relative_coords = v_uv - center;
    vec2 rotated_coords = vec2(relative_coords.x * cos(u_time) - relative_coords.y * sin(u_time), relative_coords.x * sin(u_time) + relative_coords.y * cos(u_time));
    vec2 rotated_uvs = rotated_coords + center;
    clamp(rotated_uvs, 0.0, 1.0); 
    vec4 rotated_color = texture2D(u_texture, rotated_uvs);
    gl_FragColor = rotated_color;*/
    
    //3.3 PIXELATION
    /*float pixelation_level = 30.0;
    vec2 pixel_size = vec2(1.0)/vec2(pixelation_level);
    vec2 coords = floor(v_uv/pixel_size);
    vec2 text_coords = coords*pixel_size;
    vec4 pixelation_color = texture2D(u_texture, text_coords);
    gl_FragColor = pixelation_color;*/
    
    
}

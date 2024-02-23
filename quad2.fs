varying vec2 v_uv;
//we can use time but we can use also an integer
uniform float u_time;
uniform sampler2D u_texture;
uniform float u_subtask;

void main()
{
    
    vec4 texture_color = texture2D(u_texture, v_uv);
    gl_FragColor = texture_color;
    
    if(u_subtask == 1.0){
        float grayscale = (texture_color[0]+texture_color[1]+texture_color[2])/3.0;
        gl_FragColor = vec4(grayscale, grayscale, grayscale, texture_color[3]);
    }
    
    
    if(u_subtask == 2.0){
        vec3 inverted_color = vec3(1.0-texture_color[0], 1.0-texture_color[1], 1.0-texture_color[2]);
        gl_FragColor = vec4(inverted_color, texture_color[3]);
    }
    
    if(u_subtask == 3.0){
        float grayscale = (texture_color[0]+texture_color[1]+texture_color[2])/3.0;
        vec3 yellow = vec3(1.0, 1.0, 0.0) * grayscale;
        gl_FragColor = vec4(yellow, texture_color[3]);
    }
    
    if(u_subtask == 4.0){
        float grayscale = (texture_color[0]+texture_color[1]+texture_color[2])/3.0;
        float threshold = 0.5;
        
        vec3 black_white = step(threshold, grayscale) * vec3(1.0); //step is either 0 or 1
        //if step == 0, then vec3(0.0, 0.0, 0.0) so pure black
        //if step == 1, then vec3(1.0, 1.0, 1.0) so pure white
        gl_FragColor = vec4(black_white, texture_color[3]);
    }
    
    
    if(u_subtask == 5.0){
        vec2 center = vec2(0.5); //we will define our center (of rectangle)
         float dist_text = distance(v_uv, center);
         float vignette = smoothstep(0.05, 0.7, dist_text);
         gl_FragColor = mix(texture_color, vec4(0.0, 0.0, 0.0, 1.0), vignette); //mix between texture color, black and the size of the vignette as a factor
        
    }
    
    if(u_subtask == 6.0){
        float blurRadius = 0.005; // Change this value based on your preference
         
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
         gl_FragColor = vec4(blurredColor, texture_color[3]);
        
    }
    
}

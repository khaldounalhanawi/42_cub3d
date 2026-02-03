```c
/*
 * ═══════════════════════════════════════════════════════════════════════════
 *                       CUB3D FUNCTION CALL HIERARCHY
 * ═══════════════════════════════════════════════════════════════════════════
 */

'main'                                  /* Entry point */
│
├── 'parse_file'                        /* Parses .cub scene file and extracts data */
│   ├── 'parse_line'                    /* Processes individual lines from file */
│   ├── 'set_texture'                   /* Stores texture paths (NO, SO, WE, EA) */
│   ├── 'set_color'                     /* Parses RGB color values for floor/ceiling */
│   └── 'build_map'                     /* Constructs 2D map grid from file data */
│
├── 'validate_data'                     /* Validates parsed scene data */
│   ├── 'check_line'                    /* Validates map line integrity */
│   └── 'find_player'                   /* Locates player spawn position and validates */
│
├── 'init_system'                       /* Initializes MLX, window, and game state */
│   │
│   ├── 'init_input'                    /* Initializes all input flags to 0 */
│   ├── 'init_player'                   /* Sets up player position and orientation */
│   │   └── 'get_player_dir'            /* Sets direction vector based on N/S/E/W character */
│   ├── 'convert_arr_to_color'          /* Converts RGB array to hexadecimal color value */
│   ├── 'mlx_init'                      /* MLX: Initializes graphics system */
│   ├── 'mlx_new_window'                /* MLX: Creates game window */
│   ├── 'load_textures'                 /* Loads all wall textures and player sprite from XPM files */
│   │   ├── 'init_texture' × 5          /* Loads North, South, East, West, Player Sprite textures */
│   │   │   ├── 'mlx_xpm_file_to_image' /* MLX: Loads XPM texture file */
│   │   │   └── 'mlx_get_data_addr'     /* MLX: Gets pixel data pointer */
│   │   ├── 'clear_data' [on error]     /* Frees initialization data */
│   │   └── 'clean_system_exit' [error] /* Cleanup and exit on failure */
│   └── 'init_frame'                    /* Creates the main rendering frame buffer */
│       ├── 'mlx_new_image'             /* MLX: Creates frame buffer image */
│       └── 'mlx_get_data_addr'         /* MLX: Gets frame pixel data pointer */
│
├── 'clear_data'                        /* Frees initialization data after system is ready */
│   └── 'free_utils'                    /* Utility functions for freeing allocated memory */
│
├── 'set_hooks'                         /* Registers all event handlers for the game */
│   ├── 'mlx_hook' × 3                  /* MLX: Registers three event handlers */
│   │   ├── 'close_window'              /* Handles window close event (X button) */
│   │   │   └── 'clean_system_exit'     /* Final cleanup and exit */
│   │   ├── 'key_press'                 /* Sets input flags when keys are pressed (W/S/A/D/Arrows) */
│   │   └── 'key_release'               /* Clears input flags when keys are released */
│   └── 'mlx_loop_hook'                 /* MLX: Registers the main game loop function */
│       └── 'update_and_render'         /* Called every frame automatically */
│           ├── 'update_position'       /* Checks input flags and updates player position/rotation */
│           │   ├── 'move_forward'      /* Collision check and move player forward */
│           │   ├── 'move_backward'     /* Collision check and move player backward */
│           │   ├── 'move_left'         /* Collision check and strafe player left */
│           │   ├── 'move_right'        /* Collision check and strafe player right */
│           │   ├── 'rot_left'          /* Rotate player view counterclockwise */
│           │   └── 'rot_right'         /* Rotate player view clockwise */
│           ├── 'cast_rays'             /* Ray-casting algorithm for all screen columns */
│           │   ├── 'create_ray_hit'    /* Creates ray hit info for single column */
│           │   └── 'calculate_distance'/* DDA algorithm to find wall intersection */
│           ├── 'draw_3d'               /* Renders 3D view with textured walls */
│           │   ├── 'draw_texture_line' /* Draws vertical textured wall stripe */
│           │   └── 'draw_floor_ceiling'/* Fills floor and ceiling with solid colors */
│           ├── 'draw_player_sprite'    /* Renders animated player weapon sprite */
│           └── 'draw_minimap'          /* Draws 2D minimap overlay */
│               ├── 'create_mini_map'   /* Initializes minimap frame buffer */
│               ├── 'draw_walls'        /* Renders map walls on minimap */
│               ├── 'draw_player'       /* Draws player position and direction */
│               └── 'draw_player_arrow' /* Draws directional arrow for player */
│
├── 'mlx_loop'                          /* MLX: Starts infinite event loop until window is closed */
│
└── 'clean_system_exit'                 /* Final cleanup and program exit */
```
```c
/* ═══════════════════════════════════════════════════════════════════════════
 *                              EVENT FLOW DIAGRAM
 * ═══════════════════════════════════════════════════════════════════════════
 */

╔══════════════════════════════════════════════════════════════════════════╗
║  'USER PRESSES KEY (W/A/S/D/Arrows)'                                     ║
╠══════════════════════════════════════════════════════════════════════════╣
║  key_press()                     /* Sets game->input flags to 1 */       ║
╚══════════════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════════════╗
║  'USER RELEASES KEY'                                                     ║
╠══════════════════════════════════════════════════════════════════════════╣
║  key_release()                   /* Sets game->input flags to 0 */       ║
╚══════════════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════════════╗
║  'USER CLOSES WINDOW (X button or ESC)'                                  ║
╠══════════════════════════════════════════════════════════════════════════╣
║  close_window()                  /* Triggers cleanup and exit */         ║
║    └── clean_system_exit()       /* Frees all resources and exits */     ║
╚══════════════════════════════════════════════════════════════════════════╝

╔══════════════════════════════════════════════════════════════════════════╗
║  'EVERY FRAME (Automatic, ~60 FPS)'                                      ║
╠══════════════════════════════════════════════════════════════════════════╣
║  update_and_render()             /* Main game loop */                    ║
║    ├── update_position()         /* Processes input and moves player */  ║
║    ├── cast_rays()               /* Ray-casts all screen columns */      ║
║    ├── draw_3d()                 /* Renders textured 3D walls */         ║
║    ├── draw_player_sprite()      /* Displays animated weapon sprite */   ║
║    └── draw_minimap()            /* Renders 2D map overlay */            ║
╚══════════════════════════════════════════════════════════════════════════╝


/* ═══════════════════════════════════════════════════════════════════════════
 *                            MODULE ORGANIZATION
 * ═══════════════════════════════════════════════════════════════════════════
 *
 *  MAIN
 *    ./src/main.c                   Entry point and main program flow
 *
 *  PARSING & VALIDATION
 *    ./src/parse/parse_file.c       Scene file parsing and data extraction
 *    ./src/parse/parse_line.c       Individual line processing
 *    ./src/parse/parse_input.c      Input validation helpers
 *    ./src/parse/build_map.c        Map grid construction
 *    ./src/parse/check_line.c       Map line validation
 *    ./src/parse/find_player.c      Player spawn location and validation
 *    ./src/parse/set_texture.c      Texture path assignment
 *    ./src/parse/set_color.c        RGB color parsing
 *    ./src/parse/validate_data.c    Complete data validation
 *    ./src/parse/free_utils.c       Memory cleanup utilities
 *    ./src/parse/free_validating.c  Validation cleanup
 *
 *  INITIALIZATION & CLEANUP
 *    ./src/utils/init_system.c      System and game initialization
 *    ./src/utils/init_player.c      Player position and direction setup
 *    ./src/utils/init_images.c      Texture and frame buffer loading
 *    ./src/utils/clean_system_exit.c Memory cleanup and exit handling
 *
 *  EVENT HANDLING & GAME LOOP
 *    ./src/hooks/set_hooks.c        Event handler registration and main loop
 *    ./src/hooks/controls.c         Keyboard input handlers
 *    ./src/hooks/actions_I.c        Movement functions (forward/backward/left/right)
 *    ./src/hooks/actions_II.c       Rotation functions (left/right)
 *    ./src/hooks/updates.c          Player position update logic
 *
 *  RAY-CASTING
 *    ./src/raycast/cast_rays.c      Main ray-casting loop and hit detection
 *    ./src/raycast/calculate_distance.c DDA algorithm implementation
 *
 *  RENDERING
 *    ./src/render/draw_3d.c         3D textured wall rendering
 *    ./src/render/draw_minimap.c    2D minimap overlay
 *    ./src/render/draw_sprite_player.c Animated player weapon sprite
 *    ./src/render/basic_draws.c     Primitive drawing utilities
 *
 * ═══════════════════════════════════════════════════════════════════════════
 */
```
 * ═══════════════════════════════════════════════════════════════════════════
 */
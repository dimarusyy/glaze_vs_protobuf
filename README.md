The project is used to compare serialization/deserialization performance of glaze and protobuf.
Benchmark results :

| relative |ns/uint64_t |uint64_t/s |    err% |     total | Serialize   
|---------:|--------------------:|--------------------:|--------:|----------:|:----------  
|   100.0% |808,024.30 |  1,237.59 |    0.5% |      0.97 | `glaze_beve_serialize`
|    17.5% |        4,625,480.83 |    216.19 |    2.0% |      5.58 | `glaze_json_serialize`
|   195.8% |412,678.33 |  2,423.19 |    0.1% |      0.50 | `protobuf_serialize`   

| relative |ns/uint64_t |uint64_t/s |    err% |     total | Deserialize 
|---------:|--------------------:|--------------------:|--------:|----------:|:------------
|   100.0% |358,760.87 |  2,787.37 |    0.7% |      0.44 | `glaze_beve_deserialize`        
|     8.8% |        4,090,953.04 |    244.44 |    0.7% |      4.95 | `glaze_json_deserialize`        
|    57.4% |625,335.34 |  1,599.14 |    3.3% |      0.78 | `protobuf_deserialize`     

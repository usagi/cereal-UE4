# cereal-UE4

cereal ( C++ serialization library ) adapter for UE4 ( Unreal Engine ) types

- cereal: https://uscilab.github.io/cereal/
- UE4: http://www.unrealengine.com/

# Motivation

- JSON serializer of UE4 is ...
    - Not supported many common UE4 types; `FVector`, `FTimespan`, `FVector2D`, `FBox`, `FBox2D`, `FColor`, `FLinearColor`, `FIntPoint`, `FMatrix`, `FPlane`, `FScale`, `FShpere`, `FBigInt`, `int8`, `uint8`, `int16`, `uint16`, `int64`, `uint64`, ...
    - Implemented by inheritance model only ( using virtual functions )
        - If we use it then it will break POD ( standard layout ) of our data structure. `vtable` increase a data size and break packing of a data array.
        - It cannot use for `USTRUCT` types.
    - Very complicated and messy to use low-level APIs for a full-manually serialization. ( see [] [] )

Then, I decided to use `cereal` and I wrote the adapter library.

- cereal-UE4 is ...
    - Ofcorse, no problems for use `USTRUCT` types.
    - Supported many common UE4 types
        - `TArray`, `TMap`, `TSet`
        - `TInterval` ( with `FFloatInterval`, `FInt32Interval` )
        - `TBigInt`
        - `FString`, `FName`
        - `FDateTime`, `FTimespan`
        - `FVector`, `FVector2D`
        - `FBox`, `FBox2D`
        - `FSphere`
        - `FCapsuleShape`
        - `FLinearColor`, `FColor`
        - `FIntVector`, `FIntPoint`, `FIntVector4`, `FUintVector4`
        - `FIntRect`
        - `FMatrix`, `FMatrix2x2`
        - `FScale`, `FScale2D`, `FShear2D`
        - `FOrientedBox`
        - `FPlane`
        - `FShpere`
        - `FQuat`, `FQuat2D`
        - `FTwoVectors`
    - Ofcorse, Supported common C++ types
        - `int8`, `uint8`, `int16`, `uint16`, `int32`, `uint32` `int64`, `uint64`
        - `float`, `double`, `long double`
        - `std::string`, `std::vector`, `std::map`, ... ( see [cereal: Standard Library Support](https://uscilab.github.io/cereal/stl_support.html) )
    - Use a similar archiving methods for JSON / XML / Portable-binary.

# Usage

## 0. Deploy the cereal to your UE4 project

```sh
cd {your-project}
mkdir Thirdparty
cd Thirdparty
git clone git@github.com:USCiLab/cereal.git
```

Note: this is an example story, you can deploy any other method and any directory.

## 1. Deploy this library to your UE4 project

```sh
cd {your-project}
mkdir Thirdparty
cd Thirdparty
git clone git@github.com:usagi/cereal-UE4.git
```

Note: this is an example story, you can deploy any other method and any directory.

## 2. Add Include setting to {your-project}.Build.cs

{your-project}.Build.cs:

```cs
// 1. Add the `using`
using System.IO;

public class YourProject
  : ModuleRules
{
  public YourProject(ReadOnlyTargetRules Target)
    : base( Target )
  {
    // 2. Add below code into your setting
    {
      var base_path = Path.GetDirectoryName( RulesCompiler.GetFileNameFromType( GetType() ) );
      string third_party_path = Path.Combine( base_path, "..", "..", "Thirdparty");
      PublicIncludePaths.Add( Path.Combine( third_party_path, "cereal", "include") );
      PublicIncludePaths.Add( Path.Combine( third_party_path, "cereal-UE4", "include") );
    }
  }
}
```

## 3. Write your serialization code in your UE4 project

Now, you can serialize `FString`, `FDateTime`, `FVector` and etc. with cereal!

your-something.h:

```cpp
// cereal-UE4 serializable class(struct)
USTRUCT( BlueprintType ) struct FMySomething
{ GENERATED_BODY()
  UPROPERTY( BlueprintReadWrite ) FString String;
  UPROPERTY( BlueprintReadWrite ) FDateTime DateTime;
  UPROPERTY( BlueprintReadWrite ) FVector Vector;
  UPROPERTY( BlueprintReadWrite ) TArray< int32 > ArrayI32;
};

// cereal-UE4 external serializer definition for FMySomething type
template < typename A >
void serialize( A& a, FMySomething& in )
{
  a
  ( cereal::make_nvp( "String", in.String )
  , cereal::make_nvp( "DateTime", in.DateTime )
  , cereal::make_nvp( "Vector", in.Vector )
  , cereal::make_nvp( "ArrayI32", in.ArrayI32 )
  );
}
```

your-something.cpp:

```cpp
/* ... ( abbreviation ) ...  */

// cereal
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
// cereal-UE4
#include "cereal-UE4.hxx"
// std::stringstream
#include <sstream>

/* ... ( abbreviation ) ...  */
  
  FMySomething MySomething;
  MySomething.String = "Hello, こんにちは.";
  MySomething.DateTime = FDateTime::UtcNow();
  MySomething.Vector = FVector::UpVector();
  MySomething.ArrayI32 = { 123, -456, 789 };
  
  /* ... ( abbreviation ) ...  */
  
  std::stringstream buffer;
  {
    cereal::JSONOutputArchive a( buffer );
    a( cereal::make_nvp( "MySomething", MySomething ) );
  }
  const auto json = FString( buffer.str().data() );
  UE_LOG( LogTemp, Log, TEXT( "%s" ), *json )
  
  if
  ( !  FFileHelper::SaveStringToFile
          ( json
          , *( FPaths::ProjectDir / TEXT( "MySomething.json" ) )
          , FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM )
  )
  {
    UE_LOG( LogTemp, Fatal, TEXT( "Save Error" ) );
  }

/* ... ( abbreviation ) ...  */
```

result ( `MySomething.json` ):

```json
{
    "MySomething": {
        "String": "Hello, こんにちは.",
        "DateTime": "2018-03-29T17:59:50.595Z",
        "Vector": {
            "X": 0.0,
            "Y": 0.0,
            "Z": 1.0
        },
        "ArrayI32": [
            123,
            -456,
            789
        ]
    }
}
```

- See https://uscilab.github.io/cereal/quickstart.html if you need quickstart of cereal.
- See [example/](example/) if you need an example of all of supported type and easy testing.

# Licensing

- [MIT](LICENSE)

# Author

- © 2018 [Usagi Ito](usagi@WonderRabbitProject.net)

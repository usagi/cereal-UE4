# cereal-UE4

This is *the adapter library* of [cereal][] for [UE4][] types.

- cereal: <https://uscilab.github.io/cereal/>; C++ Serialization library, header-only
- UE4: <http://www.unrealengine.com/>; 3D Game, Architecture, Visualization Engine( Framework, Middle-ware )

## Features of this library and cereal

- Many common UE4 types are supported! // *main feature of this library!*
  - See also [§Supported types](#Supported-types) in below.
- Header-only library! // Easy for use your UE4 project.
- No problems for use `USTRUCT` types. // UE4 built-in serializer is not supported
- Ofcourse, common C++ types are supported. // UE4 build-in serializer is not supported
    - `int8`, `uint8`, `int16`, `uint16`, `int32`, `uint32` `int64`, `uint64`
    - `float`, `double`, `long double`
    - `std::string`, `std::vector`, `std::map`, ... // See also [cereal: Standard Library Support](https://uscilab.github.io/cereal/stl_support.html)
- You can use a similar methods in archiving of JSON, XML and Portable-binary.

## Supported types *in this library*

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

## Motivation

- JSON serializer of UE4 is ...
    - Not supported many common UE4 types; `FVector`, `FTimespan`, `FVector2D`, `FBox`, `FBox2D`, `FColor`, `FLinearColor`, `FIntPoint`, `FMatrix`, `FPlane`, `FScale`, `FShpere`, `FBigInt`, `int8`, `uint8`, `int16`, `uint16`, `int64`, `uint64`, ...
    - Implemented by inheritance model only ( using virtual functions )
        - If we use it then it will break POD ( standard layout ) of our data structure. `vtable` increase a data size and break packing of a data array.
        - It cannot use for `USTRUCT` types.
    - Very complicated and messy to use low-level APIs for a full-manually serialization. ( see [FJsonSerializable](http://api.unrealengine.com/INT/API/Runtime/Json/Serialization/FJsonSerializable/), [UE4/JSON/DOM](http://api.unrealengine.com/INT/API/Runtime/Json/Dom/) )

Then, I decided to use `cereal` and *I wrote this adapter library*.

## Usage

1. Prepare a thirdparty library directory:
    1. `cd <your-project>`
    2. `mkdir Thirdparty`; or anywhere else as you like
    3. `cd Thirdparty`
2. Deploy [cereal][] library.
    - `git clone git@github.com:USCiLab/cereal.git`; <- It's serialization base library
3. Deploy [cereal-UE4][] library.
    - `git clone git@github.com:usagi/cereal-UE4.git`; <- *It's this library!*
4. Add `PublicIncludePaths` settings to `<your-project>.Build.cs`; See also below (†1)
5. Write your serialization code in your UE4 project; See also below (†2)
    - And get your serialization results! (†3)

(†1): Step-4's `<your-project>.Build.cs`

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

(†2): Step-5's e.g.; Now, you can serialize `FString`, `FDateTime`, `FVector` and etc. with cereal!

`your-something.h`:

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

`your-something.cpp`:

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

(†5): Step-5's expected result.

`MySomething.json`:

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

## Licensing

- [MIT](LICENSE)

## Author

- Usagi Ito
  - <the@usagi.network>
  - <https://github.com/usagi>
  - <https://discord.gg/QsDNMbN>
  - <https://www.reddit.com/user/luatichare>
  - <https://twitter.com/USAGI_WRP>
  - <https://www.facebook.com/usagi.wrp>
  - <https://www.instagram.com/usagi_wrp/>

[cereal]: https://uscilab.github.io/cereal/
[cereal-UE4]: https://github.com/usagi/cereal-UE4/
[UE4]: https://www.unrealengine.com/

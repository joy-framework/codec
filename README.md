# codec

base64 encode/decode library for janet

## Install

Add to your `project.janet` file

```clojure
{:dependencies [{:repo "https://github.com/joy-framework/codec" :tag "b02ad8c07885cfe0e83ec04d249570831cf3e070"}]}
```

## Use

```clojure
(import codec)

(= "hello there!" (codec/decode (codec/encode "hello there!")))
```

And that's all folks

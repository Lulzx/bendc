#!/bin/sh
# Installs the official Bend into $BEND_HOME (default ~/.bend), as
# bend-lang.com/install.sh does, but a pinned version: CI uses this, so a
# new Bend release changes what CI tests only when this file changes (the
# weekly CI run tries the latest). `tools/install-bend.sh latest` runs
# bend-lang.com/install.sh itself.
#
# To move the pin: take VER and the four sums from the new release's
# install.sh (curl -fsSL https://bend-lang.com/install.sh | head -25).
set -eu

VER="2.0.32"
SHA_DARWIN_ARM64="d7debc002f59264f648dc94e45c2a9fab23e4b1ee0a390bf2acd8b1673e0cf55"
SHA_DARWIN_X64="6c3fea18ade9912e3015472fe76a2b1372acbf72b82404b3dea1a1243c5ed09e"
SHA_LINUX_ARM64="f57776d20c0b6aabf47bc9d4523522c10ecd2acde98a2615049b094bb9241523"
SHA_LINUX_X64="5c365ddb12954d0933cef751802e0f7d9875f842edcb80f9661f89cd1a9ff7b6"

if [ "${1:-}" = latest ]; then
  curl -fsSL https://bend-lang.com/install.sh | sh
  exit
fi

case $(uname -s)-$(uname -m) in
  Darwin-arm64) os=darwin arch=arm64 sum=$SHA_DARWIN_ARM64;;
  Darwin-x86_64) os=darwin arch=x64 sum=$SHA_DARWIN_X64;;
  Linux-aarch64|Linux-arm64) os=linux arch=arm64 sum=$SHA_LINUX_ARM64;;
  Linux-x86_64) os=linux arch=x64 sum=$SHA_LINUX_X64;;
  *) echo "install-bend: no Bend build for $(uname -s) $(uname -m)" >&2; exit 1;;
esac

home=${BEND_HOME:-$HOME/.bend}
name="bend-$VER-$os-$arch.tar.gz"
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
curl --proto '=https' --tlsv1.2 -fsSL -o "$tmp/$name" \
  "https://github.com/bendlang/bend/releases/download/v$VER/$name"
if command -v sha256sum >/dev/null 2>&1; then
  got=$(sha256sum "$tmp/$name" | cut -d' ' -f1)
else
  got=$(shasum -a 256 "$tmp/$name" | cut -d' ' -f1)
fi
[ "$got" = "$sum" ] || { echo "install-bend: $name does not match its sha256" >&2; exit 1; }
tar -xzf "$tmp/$name" -C "$tmp"
mkdir -p "$home/bin"
rm -rf "$home/bend2" "$home/guide"
mv "$tmp/bend/bend2" "$tmp/bend/guide" "$home/"
mv -f "$tmp/bend/bin/bend" "$home/bin/bend"
echo "install-bend: Bend $VER in $home"

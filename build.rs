#![feature(append)]

extern crate pkg_config;
extern crate gcc;

use std::env;
use std::path::PathBuf;

fn main() {
    let mut paths  = Vec::new();
    //if let Ok(ref mut info) = pkg_config::find_library("enlightenment") {
    if let Ok(ref mut info) = pkg_config::find_library("ecore") {
        paths.append(&mut info.include_paths);
    }
    if let Ok(ref mut info) = pkg_config::find_library("ecore-imf") {
        paths.append(&mut info.include_paths);
    }
    if let Ok(ref mut info) = pkg_config::find_library("ecore-x") {
        paths.append(&mut info.include_paths);
    }
    if let Ok(ref mut info) = pkg_config::find_library("ecore-evas") {
        paths.append(&mut info.include_paths);
    }

    build(&paths);
}

fn build(include_paths: &[PathBuf]) {
    let mut config = gcc::Config::new();

    for path in include_paths {
        config.include(path);
    }

    config.file("src/inpa_module.c")
        .file("src/inpa_imcontext.c")
        .compile("libinpa.a");

     let out_dir = env::var("OUT_DIR").unwrap();

    println!("cargo:rustc-link-search=native={}", out_dir);
    //println!("cargo:rustc-link-lib=static=edge");
    //println!("cargo:include={}/src", env::current_dir().unwrap().display());

}


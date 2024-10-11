import request from "@/utils/request";


export function Search(name) {
  return request({
    url: 'compare/dashboard/',
    method: 'get',
    params: {
      name: name
    }
  })
}

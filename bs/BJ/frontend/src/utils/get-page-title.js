import defaultSettings from '@/settings'

const title = defaultSettings.title || 'Price Pulse'

export default function getPageTitle(pageTitle) {
  if (pageTitle) {
    return `${pageTitle} - ${title}`
  }
  return `${title}`
}
